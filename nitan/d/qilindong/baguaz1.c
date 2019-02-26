// Room: 八卦圖

#include <ansi.h>
inherit ROOM;
string* dirs = ({
        "坎", "坤", "離", "乾",
        "艮", "震", "巽", "兑"
        });
void create()
{
        set("short",HIR"八陣圖"NOR);
        set("long", @LONG
你一踏進陣中只覺得四周變得天昏地暗。這裏橫七豎八的堆放着
各種巨石，細心一看發覺每個石頭擺放位置恰到好處，暗合八卦原理
，相傳是三國時代諸葛亮留下來的陣法，環環想扣，若想出過此陣並
非易事。
LONG
);      
        set("outdoors","tianyu");
        set("exits", ([
                "坎" : __DIR__"baguaz0",
                "坤" : __DIR__"baguaz0",
                "離" : __DIR__"baguaz0",
                "乾" : __DIR__"baguaz0",
                "艮" : __FILE__,
                "震" : __FILE__,
                "巽" : __FILE__,
                "兑" : __FILE__,
        ]));
        setup();
}
void init()
{
        object ob = this_player();
        int step, temp, count;
        if ( !ob->query_temp("bagua_start"))
        {
                ob->set_temp("bagua_start", 1);
                ob->set_temp("bagua_step", 1);
                ob->set_temp("bagua_temp", 0);
                ob->set_temp("bagua_count", 1);
        }
        temp  = ob->query_temp("bagua_temp");
        count = ob->query_temp("bagua_count");
        temp  = temp * 2+1;
        if (count < 3)
        {
                count++;
        }
        else
        {
                count = 1;
                step = ob->query_temp("bagua_step");
                if (temp == ob->query_temp("bagua_" + step))
                 {
                        if (step == 8)
                         {
                                ob->delete_temp("bagua_start");
                                ob->delete_temp("bagua_step");
                                ob->delete_temp("bagua_temp");
                                ob->delete_temp("bagua_count");
                                write(HIC"你反踏“震”位，撲“乾”位，突然眼前一亮，"+HIR+dirs[random(sizeof(dirs))]+HIC+"位上現出空位，你趕忙踏了過去。\n"NOR);
                                ob->move(__DIR__"qilindong", 1);
                                ob->set_temp("bagua_over",1);
                                tell_room(environment(ob), "突然，石陣中現出一個缺口，" + ob->name() + "趕緊閃身而出。\n");
                                return;
                        }
                        tell_object(ob,HIY"你發現剛才走過的路徑暗合八卦，心中若有所悟！\n"NOR);
                        ob->add_temp("bagua_step", 1);
                }
                else {
                        ob->delete_temp("bagua_start");
                        ob->delete_temp("bagua_step");
                        ob->delete_temp("bagua_temp");
                        ob->delete_temp("bagua_count");
                        write(CYN"你發覺自己踩錯了方位，陣中石陣更加變幻末測了，只好趕快搶回起始點！\n");
                        ob->move(__DIR__"dongkou");
                        tell_room(environment(ob), HIR"\n只見"+ob->name()+
                                  "朗朗蹌蹌從石陣中退了出來。\n\n"NOR);
                        return;
                }
                temp = 0;
        }
        ob->set_temp("bagua_temp", temp);
        ob->set_temp("bagua_count", count);
}
