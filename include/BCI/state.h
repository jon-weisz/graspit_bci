#ifndef STATE_H
#define STATE_H

#include <QState>

class State : public QState
{
    Q_OBJECT
public:
    explicit State( const QString& name, QState* parent = 0 );
    explicit State( const QString& name, const QString& prefix, QState* parent = 0 );

    QString name() const { return m_name; }
    QString prefix() const { return m_prefix; }

public slots:
    void setName( const QString& name ) { m_name = name; }
    void setPrefix( const QString& prefix ) { m_prefix = prefix; }
    void button2Clicked(){}
    void button3Clicked(){}
    void button4Clicked(){}

protected:
    virtual void onEntry( QEvent* e );
    virtual void onExit( QEvent* e );

protected:
    QString m_name;
    QString m_prefix;
};

#endif
