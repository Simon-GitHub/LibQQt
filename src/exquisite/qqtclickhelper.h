#ifndef QQTCLICKHELPER_H
#define QQTCLICKHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>

#if 0
#define p2debug() p2line()
#else
#define p2debug() QNoDebug()
#endif

/**
 * QQtClickHelper
 * 这个Helper是给Widget响应按钮事件用的
 * 主要用于为QQtWidget系列添加按钮信号识别帮助
 *
 * 支持
 * click
 * longClick
 * 不支持DoubleClick, doubleClick会导致click延时
 *
 * 可以统计按键次数
 */
class QQTSHARED_EXPORT QQtClickHelper : public QObject
{
    Q_OBJECT

public:
    explicit QQtClickHelper ( QObject* parent = 0 );
    virtual ~QQtClickHelper();

    //调用于userWidget相对应的Event里
    //允许重写
public:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget = 0 );

signals:
    void click();
    void longClick();

signals:
    void clickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );

signals:
    void clickWithPointF ( QPointF point );
    void longClickWithPointF ( QPointF point );

    //optional
public:
    //设置longClick超时 default:1200ms
    void setLongClickInterval ( int millSecond = longClickInterval );
    int getLongClickInterval() const;

    quint32 clickNum() const;
    quint32 longClickNum() const;
    quint64 totalClickNum() const;

    /**
     * 以下用于内部
     */
public:
    Q_ENUMS ( QQtClickType )
    Q_PROPERTY ( int mLongClickInterval READ getLongClickInterval WRITE setLongClickInterval )

    typedef enum
    {
        QQtNullClick = 0,

        QQtClick,
        QQtLongClick,

        QQtDoubleClick,

        QQtMaxClick
    } QQtClickType;

protected:
    //这个语法比较难,只有整型有特权.
    static const int longClickInterval = 1200;

    //用于记录点击到了什么状态.
    QQtClickType mClickType;

    //用于记录按钮的位置
    QPoint mPoint;

    int mLongClickInterval;

    //click 检测使用
    QTime t1;//press relase
    QTime t2;//release

    //click num
    virtual void checkClickNum();

    quint32 nClickNum;
    quint32 nLongClickNum;
    quint64 nTotalClickNum;
};

#endif // QQTCLICKHELPER_H