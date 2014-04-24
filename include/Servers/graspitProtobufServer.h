#ifndef GRASPITPROTOBUFSERVER_H
#define GRASPITPROTOBUFSERVER_H
#include <QtNetwork>
#include <QTimer>
class GraspitProtobufMessage;
class DrawableFrame;

class GraspitProtobufConnection : public QObject
{
    Q_OBJECT
public:
    GraspitProtobufConnection(QObject * parent, QTcpSocket * socket,
                              unsigned int maximum_len = 5000);
    ~GraspitProtobufConnection();

signals:
    void updateFrame(DrawableFrame & drawing);

private:
    //! Individual Socket connection
    QTcpSocket *sock;

    //! Maximum size of socket's buffer
    unsigned int maxLen;

    //! Graspit message to read into
    GraspitProtobufMessage *msg;

private slots:
    //! Read the message and act on it.
    void parseMessage();

    //! Read the message from the wire and try to parse it.
    bool readMessage();
};

class GraspitProtobufServer : public QTcpServer
{
    Q_OBJECT
public:
    GraspitProtobufServer(unsigned int port_num,QObject * parent = 0);
private slots:
    void onConnection();
};

#endif // GRASPITPROTOBUFSERVER_H
