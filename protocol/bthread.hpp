#ifndef _BTHREAD_H
#define _BTHREAD_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

// ASIO background thread
//-----------------------------------------------------------------------------
// Thanks to Vaclav Vesely and Christopher Kohlhoff
// http://boost.2283326.n4.nabble.com/asio-How-to-write-custom-async-event-provider-td2604301.html
// ----------------------------------------------------------------------------
// This is modified version to compile with GCC 4.6 -fpermissive
// Pavel Slechta <slechta at email dot cz>
//-----------------------------------------------------------------------------

template<typename Demuxer>
class async_object
{
public:
    typedef Demuxer demuxer_type;

public:

    async_object(demuxer_type& demuxer):
        m_demuxer(demuxer)
    {
    }

    demuxer_type& demuxer()
    {
        return m_demuxer;
    }

protected:
    demuxer_type& m_demuxer;
};

//-----------------------------------------------------------------------------

template<typename Demuxer>
class background_worker:
    public async_object<Demuxer>
{
public:

	typedef typename background_worker<Demuxer>::demuxer_type demuxer_type;

    background_worker(Demuxer& demuxer):
        async_object<Demuxer>(demuxer),
        m_work_demuxer(),
        m_dummy_work(new boost::asio::io_service::work(m_work_demuxer))
    {
    }

    ~background_worker()
    {
        m_dummy_work.reset();
        if(m_work_thread)
            m_work_thread->join();
    }

private:

    template<typename Function, typename Handler>
    class run_proc
    {
    public:

        run_proc(demuxer_type& demuxer, Function function, Handler handler):
            m_demuxer(demuxer),
            m_work(demuxer),
            m_function(function),
            m_handler(handler)
        {
        }

        void operator()()
        {
            m_function();
            m_demuxer.post(m_handler);
        }

    private:
        demuxer_type& m_demuxer;
        typename demuxer_type::work m_work;
        Function m_function;
        Handler m_handler;
    };

public:

    template<typename Function, typename Handler>
    void async_run(Function function, Handler handler)
    {
        m_work_demuxer.post(run_proc<Function, Handler>(demuxer(), function,
            handler));
        if(!m_work_thread)
        {
            m_work_thread.reset(new boost::thread(boost::bind(
                &background_worker::work_thread_proc, this)));
        }
    }

private:

    void work_thread_proc()
    {
        m_work_demuxer.run();
    }

private:
    boost::asio::io_service m_work_demuxer;
    boost::scoped_ptr<boost::thread> m_work_thread;
    boost::scoped_ptr<boost::asio::io_service::work> m_dummy_work;
};

//-----------------------------------------------------------------------------

/*
boost::mutex cout_mutex;

void wait(int seconds)
{
    {
        boost::mutex::scoped_lock lock(cout_mutex);
        std::cout << "Wait for " << seconds << " seconds" << std::endl;
    }
    boost::xtime xt;
    boost::xtime_get(&xt, boost::TIME_UTC);
    xt.sec += seconds;
    boost::thread::sleep(xt);
}

void wait_finished()
{
    {
        boost::mutex::scoped_lock lock(cout_mutex);
        std::cout << "Waiting finished." << std::endl;
    }
}
*/

//-----------------------------------------------------------------------------
/*
int main(int argc, char *argv[])
{
    boost::asio::io_service ios;
    
    background_worker<boost::asio::io_service> bg_thread(ios);
    background_worker<boost::asio::io_service> bg_thread2(ios);
    
    bg_thread.async_run(boost::bind(wait, 5), wait_finished);
    bg_thread2.async_run(boost::bind(wait, 5), wait_finished);
    ios.run();

    bg_thread.async_run(boost::bind(wait, 10), wait_finished);
    
    ios.reset();
    ios.run();
} 
*/

#endif
