#include "computer.h"

Computer::Computer(int size)
{
    fieldSize = size;
    memory.direction = 0;
    memory.pos.setY(-1);
    memory.pos.setX(-1);
}

QVector<Cell> Computer::create()
{
    comfield.fill(Empty,fieldSize*fieldSize);
    qsrand(QDateTime::currentMSecsSinceEpoch());
    int numShip;
    int sizeShip;
    switch(fieldSize)
    {
        case 8:
            sizeShip = 2;
            numShip = 2;
        break;
        case 10:
            sizeShip = 3;
            numShip = 3;
        break;
        case 12:
            sizeShip = 3;
            numShip = 3;
        break;
    }

    bool b;
    for(int n=sizeShip;n>=0;n--){
        if (fieldSize == 12 && n == 2)
            numShip++;
        for(int m=0;m<=numShip-n;m++){
            do{
                int x = qrand()% fieldSize;;
                int y = qrand() % fieldSize;
                int kx = qrand() % 2;
                int ky = (kx==0)?1:0;
                b = true;
                for(int i=0;i<=n;i++)
                {
                    int xx = x +kx*i;
                    int yy = y +ky*i;
                    if(!(xx<fieldSize && yy <fieldSize && check(xx, yy ) == Empty && check(xx+1, yy ) == Empty && check(xx-1, yy) == Empty && check(xx, yy+1) == Empty && check(xx, yy-1) == Empty && check(xx+1, yy+1) == Empty && check(xx-1, yy-1) == Empty && check(xx+1, yy-1) == Empty && check(xx-1, yy+1) == Empty)) b = false;
                }
                if(b) for(int i=0;i<=n;i++) comfield[(x+kx*i)+(y+ky*i)*fieldSize] = Ship;
            }while(!b);
        }
    }
    for (int i=0; i<fieldSize*fieldSize;i++)
    {
        if (comfield[i] == Hit)
            comfield[i] = Empty;
    }
    return comfield;
}

Cell Computer::check(int x, int y)
{
    if (x>=0 && y>=0 && x<fieldSize && y<fieldSize)
        return comfield[x+y*fieldSize];
    return Empty;
}

QPoint Computer::attack(Battlefield *field)
{
    if (field->status(memory.pos).alive == true)
    {
        if (memory.direction == 0)
        {
            int rand = qrand()% 2;
            if (rand == 0)
                memory.direction = 1;
            else
                memory.direction = 10;
            rand = qrand()% 2;
            if (rand == 0)
            {
                memory.direction = memory.direction*(-1);
            }
            ShotField result;
            do
            {
                switch (memory.direction)
                {
                case -1: result = field->doshot(memory.pos.x()-1,memory.pos.y());
                    break;
                case -10: result = field->doshot(memory.pos.x(),memory.pos.y()-1);
                    break;
                case 1: result = field->doshot(memory.pos.x()+1,memory.pos.y());
                    break;
                case 10: result = field->doshot(memory.pos.x(),memory.pos.y()+1);
                    break;
                }
                qDebug()<<"ffg"<<memory.direction;
                if (!(result.shot))
                {
                    memory.direction = memory.direction*(-1);
                    qDebug()<<"ffg"<<memory.direction;
                    switch (memory.direction)
                    {
                    case -1: result = field->doshot(memory.pos.x()-1,memory.pos.y());
                        break;
                    case -10: result = field->doshot(memory.pos.x(),memory.pos.y()-1);
                        break;
                    case 1: result = field->doshot(memory.pos.x()+1,memory.pos.y());
                        break;
                    case 10: result = field->doshot(memory.pos.x(),memory.pos.y()+1);
                        break;
                    }
                    if (!(result.shot))
                        if (memory.direction%10 == 0)
                            memory.direction = memory.direction/10;
                        else
                            memory.direction = memory.direction*10;
                }
            }while (!(result.shot));
            QPoint pos;
            pos = memory.pos;
            qDebug()<<"ffffff"<<pos.x()<<pos.y()<<memory.direction;
            switch (memory.direction)
            {
            case -1: pos.setX(pos.x()-1);
                break;
            case -10: pos.setY(pos.y()-1);
                break;
            case 1: pos.setX(pos.x()+1);
                break;
            case 10: pos.setY(pos.y()+1);
                break;
            }
            if (!(result.hit))
            {
                memory.direction = 0;
                qDebug()<<"ffffff";
            }
            else
                memory.pos = pos;
            qDebug()<<"ffffff"<<pos.x()<<pos.y();
            return pos;
        }
        else
        {
            ShotField result;
            switch (memory.direction)
            {
            case -1: result = field->doshot(memory.pos.x()-1,memory.pos.y());
                break;
            case -10: result = field->doshot(memory.pos.x(),memory.pos.y()-1);
                break;
            case 1: result = field->doshot(memory.pos.x()+1,memory.pos.y());
                break;
            case 10: result = field->doshot(memory.pos.x(),memory.pos.y()+1);
                break;
            }
            if (!(result.shot))
            {
                memory.direction = memory.direction*(-1);
                do
                {
                    switch (memory.direction)
                    {
                    case -1: memory.pos.setX(memory.pos.x()-1);
                        break;
                    case -10: memory.pos.setY(memory.pos.y()-1);
                        break;
                    case 1: memory.pos.setX(memory.pos.x()+1);
                        break;
                    case 10: memory.pos.setY(memory.pos.y()+1);
                        break;
                    }
                    switch (memory.direction)
                    {
                    case -1: result = field->doshot(memory.pos.x()-1,memory.pos.y());
                        break;
                    case -10: result = field->doshot(memory.pos.x(),memory.pos.y()-1);
                        break;
                    case 1: result = field->doshot(memory.pos.x()+1,memory.pos.y());
                        break;
                    case 10: result = field->doshot(memory.pos.x(),memory.pos.y()+1);
                        break;
                    }
                }while (!(result.shot));
            }
            QPoint pos;
            pos = memory.pos;
            qDebug()<<"ffffff"<<pos.x()<<pos.y()<<memory.direction;
            switch (memory.direction)
            {
            case -1: pos.setX(pos.x()-1);
                break;
            case -10: pos.setY(pos.y()-1);
                break;
            case 1: pos.setX(pos.x()+1);
                break;
            case 10: pos.setY(pos.y()+1);
                break;
            }
            if (result.hit or (!(result.shot)))
                memory.pos = pos;
            return pos;
        }
    }
    else
    {
        QPoint pos;
        pos.setX(-1);
        pos.setY(-1);
        int i = 0;
        while (field->check(pos.x(), pos.y()) != Ship && i < 1)
        {
        do
        {
        qsrand(QDateTime::currentMSecsSinceEpoch());
        int random = qrand()% fieldSize;
        pos.setX(random);
        random = qrand()% fieldSize;
        pos.setY(random);
        }
        while ((field->check(pos.x(), pos.y()) == Hit) or ((field->check(pos.x(), pos.y()) == Shot)));
        i = i +1;
        }
        memory.pos = pos;
        memory.direction = 0;
        qDebug()<< "f"<<i;
        return pos;
    }
}
