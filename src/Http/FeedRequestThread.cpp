/*
 * FeedRequestThread.cpp
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

#include "Http/FeedRequestThread.h"

using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;
using namespace Osp::Base::Utility;
using namespace Osp::Net;
using namespace Osp::Net::Http;
using namespace Osp::Ui::Controls;
using namespace Osp::Io;

FeedRequestThread::FeedRequestThread() :
    pTransaction(null), pSession(null), started(false) {

}

FeedRequestThread::~FeedRequestThread() {
    delete pTransaction;
    delete pSession;
}

result FeedRequestThread::Construct(Osp::Ui::Controls::Form * listenerForm) {
    AppAssertf(listenerForm != null, "listenerForm is null");
    pListenerForm = listenerForm;
    return Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
}

result FeedRequestThread::DownloadFeed(Osp::Base::String &feedUrl, Osp::Base::String &feedDownloadPath) {

	/* Saves params in class member variables */
    rssFeedUrl = feedUrl;
    rssFeedDownloadPath = feedDownloadPath;

    /* Start the thread */
    return Start();

}

bool FeedRequestThread::OnStart(void) {
    AppLog("Starting FeedRequestThread");
    started = true;

    result r = E_SUCCESS;

    HttpRequest * pRequest = null;

    pSession = new HttpSession();

    r = pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null, rssFeedUrl, null);
    if (IsFailed(r)) {
        AppLog("Cannot construct HttpSession: %s", GetErrorMessage(r));
        AppLog("Request url is: \"%S\"", rssFeedUrl.GetPointer());
        delete pSession;
        return r;
    }

    pSession->SetAutoRedirectionEnabled(true);
    pTransaction = pSession->OpenTransactionN();

    r = pTransaction->AddHttpTransactionListener(*this);
    if (IsFailed(r))
        goto CATCH;

    pRequest = const_cast<HttpRequest*> (pTransaction->GetRequest());

    r = pRequest->SetUri(rssFeedUrl);
    if (IsFailed(r))
        goto CATCH;

    r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
    if (IsFailed(r))
        goto CATCH;

    r = pTransaction->Submit();
    if (IsFailed(r))
        goto CATCH;

    AppLog("HTTP Request started");

    return true;

    CATCH:

    AppLog("Error starting http request: %s", GetErrorMessage(r));
    pListenerForm->SendUserEvent(USER_EVENT_TRANSACTION_ABORTED, null);
    this->Stop();

    return !IsFailed(r);
}

void FeedRequestThread::OnStop(void) {
    started = false;
}

bool FeedRequestThread::IsRunning() {
	return started;
}

/* Osp::Net::Http::IHttpTransactionEventListener */

void FeedRequestThread::OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession,
                                                 Osp::Net::Http::HttpTransaction& httpTransaction,
                                                 int availableBodyLen) {

    HttpResponse* pHttpResponse = httpTransaction.GetResponse();
    if (pHttpResponse->GetHttpStatusCode() != HTTP_STATUS_OK) {
    	pListenerForm->SendUserEvent(USER_EVENT_TRANSACTION_ABORTED, null);
    	return;
    }

    ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();

    File *file = new File();
    file->Construct(rssFeedDownloadPath, L"w+");
    file->Write(*pBuffer);

    delete file;
    delete pBuffer;

}

void FeedRequestThread::OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession,
                                             Osp::Net::Http::HttpTransaction& httpTransaction,
                                             result r) {

	AppLog("Error: %s", GetErrorMessage(r));

	this->Stop();
    pListenerForm->SendUserEvent(USER_EVENT_TRANSACTION_ABORTED, null);

}

void FeedRequestThread::OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession,
                                                  Osp::Net::Http::HttpTransaction& httpTransaction,
                                                  int recommendedChunkSize) {
	/* Not used */
}

void FeedRequestThread::OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession,
                                                     Osp::Net::Http::HttpTransaction& httpTransaction,
                                                     int headerLen,
                                                     bool rs) {
	/* Not used */
}

void FeedRequestThread::OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession,
                                               Osp::Net::Http::HttpTransaction& httpTransaction) {

    this->Stop();
    pListenerForm->SendUserEvent(USER_EVENT_DATA_AVAILABLE, null);

}

void FeedRequestThread::OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession,
                                                               Osp::Net::Http::HttpTransaction& httpTransaction,
                                                               Osp::Base::String* pCert) {
	/* Not used */
}

