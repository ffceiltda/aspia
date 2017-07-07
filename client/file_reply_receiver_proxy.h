//
// PROJECT:         Aspia Remote Desktop
// FILE:            protocol/file_reply_receiver_proxy.h
// LICENSE:         Mozilla Public License Version 2.0
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_CLIENT__FILE_REPLY_RECEIVER_PROXY_H
#define _ASPIA_CLIENT__FILE_REPLY_RECEIVER_PROXY_H

#include "base/macros.h"
#include "client/file_reply_receiver.h"

#include <mutex>

namespace aspia {

class FileReplyReceiverProxy
{
public:
    bool OnDriveListRequestReply(std::unique_ptr<proto::DriveList> drive_list);
    bool OnDriveListRequestFailure(proto::RequestStatus status);

    bool OnFileListRequestReply(std::unique_ptr<proto::FileList> file_list);
    bool OnFileListRequestFailure(proto::RequestStatus status);

    bool OnCreateDirectoryRequestReply(proto::RequestStatus status);
    bool OnRemoveRequestReply(proto::RequestStatus status);
    bool OnRenameRequestReply(proto::RequestStatus status);

private:
    friend class FileReplyReceiver;

    explicit FileReplyReceiverProxy(FileReplyReceiver* receiver);

    // Called directly by FileReplyReceiver::~FileReplyReceiver.
    void WillDestroyCurrentReplyReceiver();

    FileReplyReceiver* receiver_;
    std::mutex receiver_lock_;

    DISALLOW_COPY_AND_ASSIGN(FileReplyReceiverProxy);
};

} // namespace aspia

#endif // _ASPIA_CLIENT__FILE_REPLY_RECEIVER_PROXY_H
