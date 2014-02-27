#include "graspitProtobufServer.h"
#include "Drawable.pb.h"
#include "GraspitMessage.pb.h"
#include "debug.h"

#include "BCI/bciService.h"

GraspitProtobufConnection::GraspitProtobufConnection(QObject *parent, QTcpSocket *socket,
                                                     unsigned int maximum_len) :
    QObject(parent),
    sock(socket),
    max_len(maximum_len)
{
    connect(sock, SIGNAL(readyRead()),this,SLOT(parseMessage()));
    msg = new GraspitProtobufMessage;
}

GraspitProtobufConnection::~GraspitProtobufConnection()
{
    sock->deleteLater();
    delete msg;
}

void GraspitProtobufConnection::parseMessage()
{
  if (!readMessage()){
      DBGP("GraspitProtobufConnection::parseMessage::Failed to parse message")
      return;
  }
  DrawableFrame drawableFrame = msg->drawable_frame();
  BCIService::getInstance()->emitDrawableFrame(&drawableFrame);
}

bool GraspitProtobufConnection::readMessage()
{

   QByteArray inputByteArray = sock->readAll();

   return msg->ParseFromArray(inputByteArray.data(), inputByteArray.size());
}


GraspitProtobufServer::GraspitProtobufServer(unsigned int port_num, QObject * parent ) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
    this->listen(QHostAddress::Any,port_num);
}

void GraspitProtobufServer::onConnection()
{

    QTcpSocket *clientQTcpSocketConnection = nextPendingConnection();

    GraspitProtobufConnection *newGraspitProtobufConnection = new GraspitProtobufConnection(NULL, clientQTcpSocketConnection);
    connect(clientQTcpSocketConnection, SIGNAL(disconnected()),newGraspitProtobufConnection, SLOT(deleteLater()));
}
