#include "manager.h"
#include "worker.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Created" << this << QThread::currentThread();
}

void Manager::start()
{
    // in 'start()' we initialize our connections with connect
    for(int i = 0; i < 3; ++i)
    {
        Worker *worker = new Worker();  // no parent <-- this worker is a QRunnable
        worker->setAutoDelete(true);    // On QRunnables we dont want to take care of explicitly, we call the setter 'setAutoDelete'
                                        // and set its param to 'true'
        connect(worker, &Worker::started, this, &Manager::started, Qt::QueuedConnection);   // <- Worker is connecting to Manager and tells started:started
        connect(worker, &Worker::finished, this, &Manager::finished, Qt::QueuedConnection); // <- Worker is connecting to Manager and tells finished:finished
        connect(this, &Manager::work, worker, &Worker::work, Qt::QueuedConnection);         // <- Manager 'work' is connecting to Worker 'work'

        QThreadPool::globalInstance()->start(worker); // <-- the global instance of QThreadPool is there right away when the application starts
    }
}

void Manager::started() // it is the eventloop that wraps calls and has the information who is the callee(sender) of the call to 'started' slot
{
    //this is what gets Called from the Worker ... the Worker tells the Manager "Hey guy, I just started to work", so to say.

    Worker* worker = qobject_cast<Worker*>(sender()); // <- sender() then can return a QObject* (pointer)
                                                      // since in this case we know what type the callee is,
                                                      // we can right away cast it to a Worker* (pointer)
                                                      // otherwise we might need to check that first
                                                      // if the situation would have to be more dynamic for some reason
    if(!worker) return;                               // anyway... we want to avoid failing fatally

    qInfo() << "Started" << worker << QThread::currentThread();

    // tell the worker to work
  //worker->work(); // DO NOT DO THIS AT HOME! OR IN YOUR JOB. Just don't!
                    // Since the Manager was put on the stack in the main thread and is just in that thread...
                    // this would call the 'work()' into the main-thread. since we hold the pointer.
                    // and I'd guess this is just the way how pointers work in C++ we pointing to the function we want to
                    // load into OUR(main-thread) paging and process it there... and that's just what happens.
    //instead:
    emit work();    // our signal on the manager which informs or in effect kicks off the 'connected' work in the worker,
                    // in the thread it actually is supposed to live in. Or at least that is what even most Qt Developers say
                    // it SHOULD WORK . But it does not. Since in effect we have created the Worker on the main thread . ! .
                    // this is still running with the main thread.
                    // we leave that one in Code so we can see how we would fail by reading the log messages.
                    // this should make it clear
                    // and the note you have to pin on your mind when working with Threads this way in Qt is:
                    // FOR RUNNING SOMETHING IN THE AUTOMANAGED THREADs of the ThreadPool,
                    // we ALWAYS want to AVOID ANY OUTSIDE STIMULI FROM ANYWHERE ELSE BUT THE ACTUAL WORKERS
                    // ---run()--- method.
}

void Manager::finished()
{
    Worker* worker = qobject_cast<Worker*>(sender());
    if(!worker) return;

    qInfo() << "Finished" << worker << QThread::currentThread();
}

void Manager::quit()
{

}
