// Room: /d/huijiang/zongduo.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;
#include <ansi.h>;

int flag=0;
int get=1;
void hit();
void create()
{
        set("short", "紅花會總舵");
        set("long", @LONG
這裏是紅花會的總舵，大堂上站滿了紅花會的弟子。他們的臉上表
情肅穆，每個人的右手都緊握着自己的兵刃，中間的椅子空着，看來總
舵主陳家洛不在，兩旁的香爐(xiang lu)散發出繚繚的青煙，更是襯托
出一股神聖的氛圍。
LONG );
        set("valid_startroom", 1);        
        set("exits", ([
                "southdown" : __DIR__"zoulang2",
                "west"      : __DIR__"goldroom",
        ]));
        set("item_desc", ([
                "xiang lu" : "一個古色古香的青銅香爐，一股淡淡的香氣從裏面不時的冒出來。\n",
        ]));
        set("objects", ([
                CLASS_D("honghua")+"/wu-chen" : 1,
                CLASS_D("honghua")+"/zhao-banshan" : 1,
                __DIR__"npc/dizi" : 2,
        ]));
        set("coor/x", -50070);
        set("coor/y", 9150);
        set("coor/z", 20);
        setup();
        "/clone/board/honghua_b"->foo();
}
void init()
{
        add_action("do_tui", "tui");
        add_action("do_tui", "move");
        add_action("do_wedge", "insert");
        add_action("do_wedge", "wedge");
}
int do_tui(string arg)
{
        object me=this_player();

        if(!arg || arg!="xiang lu")
                return notify_fail("你要推什麼？\n");
        if( query("combat_exp", me)<200000 )
                return notify_fail("你的功夫太差。無法推動香爐。\n");
        else if ( flag==0 )
                {
                        flag=1;
                        message_vision("只聽“咔嚓”一響，香爐上現出一個小洞。\n", me);
                        set("item_desc", ([
                                "xiang lu" : "一個古色古香的青銅香爐，一股淡淡的香氣從裏面不時的冒出來，上面有一個小洞，好像可以插入什麼東西！\n",
                            ]));
                }
                else message_vision("香爐已經推不動了！\n", me);

        return 1;
}

int do_wedge(string arg)
{
         object me=this_player();

        if( !arg || arg!="honghua ling" )
                return notify_fail("你要把什麼東西插入香爐？\n");

        if( me->is_busy() ) return notify_fail("你正忙着呢。\n");
        else if ( get==1 && flag==1 && present("honghua ling", me) &&
                        !(present("honghualing",query("zizhi", me))) )
                {
                        message_vision("$N試着把紅花令插入了香爐。\n",me);
                        message_vision( HIR"只聽香爐裏面咔嚓亂響，好像是觸動了什麼機關。\n"NOR,me);
                        me->start_busy(2);
                        hit();
                }
                else 
                {
                        if ( flag==0 )
                                return notify_fail("香爐上連洞都沒有，什麼東西也插不進去！\n");
                        if ( !present("honghua ling", me) ||
                                (present("honghualing",query("zizhi", me))) )
                                return notify_fail("你不能插這種東西進去！\n");
                        if ( get==0 )
                                return notify_fail("雪中蓮已經被人拿走了！\n");
                }
        return 1;
}

void hit()
{
        object ob, me = this_player();

        message_vision("突然只聽“嗖”的一聲，從香爐中射出三支出鐵箭！\n", me);
        if( random(query("kar", me))<20 )
        {
                message_vision( HIR"$N眼前一花，來不及躲閃，三箭齊齊的釘在$N的胸口。\n"NOR, me);
                me->unconcious();
        }
        else {
                message_vision( HIG"$N連忙一個側身，險險的避開了。\n"NOR,me );
                message_vision( HIG"香爐慢慢轉動，露出一朵"NOR,me);
                message_vision( HIW"雪中蓮"NOR,me);
                message_vision( HIG"，$N趕忙一把搶在手中。\n"NOR,me);
                ob = new(NOSTRUM_DIR"xuezhonglian" );
                me->start_busy(2);
                 ob->move(me);
                     ob = present("honghua ling", me);
                destruct(ob);
                get=0;
        }        
        return;
}
 