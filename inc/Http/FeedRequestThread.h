/*
 * FeedRequestThread.h
 *
 * Created by: Dr. Strangecode
 * ---------------------------------------------
 * This is free code, it can be used, modified, 
 * destroyed, raped and whatever without limits.
 * I own no copyrights over it.
 * This code is provided AS IS without warranty
 * of any kind either expressed or implied, 
 * including but not limited to the implied 
 * warranties of merchantability and/or fitness 
 * for a particular purpose.
 * ---------------------------------------------
 * For more free code visit http://drstrangecode.org
 */

#ifndef FEEDREQUEST_H_
#define FEEDREQUEST_H_

#include <FBase.h>
#include <FNet.h>
#include <FIo.h>
#include <FUi.h>

class FeedRequestThread : public Osp::Base::Runtime::Thread,
        public Osp::Net::Http::IHttpTransactionEventListener {

    public:
	    /* User event to notify that data have been
	     * downloaded and saved correctly
	     * */
        static const RequestId USER_EVENT_DATA_AVAILABLE = 1132;
	    /* User event to notify that data cannot be
	     * downloaded due to some error
	     * */
        static const RequestId USER_EVENT_TRANSACTION_ABORTED = 1133;

    private:

        Osp::Net::Http::HttpTransaction * pTransaction;
        Osp::Net::Http::HttpSession * pSession;

        /* A Form to notify about success or failure */
        Osp::Ui::Controls::Form * pListenerForm;

        Osp::Base::String rssFeedUrl;
        Osp::Base::String rssFeedDownloadPath;

        bool started;

    public:
        FeedRequestThread();
        virtual ~FeedRequestThread();
        result Construct(Osp::Ui::Controls::Form * listenerForm);
        result DownloadFeed(Osp::Base::String &feedUrl, Osp::Base::String &feedDownloadPath);

        bool IsRunning();

        /* Osp::Base::Runtime::Thread */

        virtual bool OnStart(void);
        virtual void OnStop(void);

        /* Osp::Net::Http::IHttpTransactionEventListener */

        void OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession,
                                      Osp::Net::Http::HttpTransaction& httpTransaction,
                                      int availableBodyLen);

        void OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession,
                                  Osp::Net::Http::HttpTransaction& httpTransaction,
                                  result r);

        void OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession,
                                       Osp::Net::Http::HttpTransaction& httpTransaction,
                                       int recommendedChunkSize);

        void OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession,
                                          Osp::Net::Http::HttpTransaction& httpTransaction,
                                          int headerLen,
                                          bool rs);

        void OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession,
                                    Osp::Net::Http::HttpTransaction& httpTransaction);

        void
        OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession,
                                               Osp::Net::Http::HttpTransaction& httpTransaction,
                                               Osp::Base::String* pCert);
};

#endif /* FEEDREQUEST_H_ */
