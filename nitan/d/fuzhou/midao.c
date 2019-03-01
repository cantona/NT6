// room: midao.c

#include <room.h>

inherit ROOM;
int do_press(string arg);

void create()
{ 
       set("short", "密道");
       set("long", @TEXT
這是水井裏的一個密道。周圍都是些機關，只有出口很明顯在哪裏。
濕漉漉的牆壁上有四塊石板，分別刻着１、２、３、４。旁邊還有一個
鐵板(tieban)扔在地上。
TEXT );
        set("exits", ([
            "out" : __DIR__"well",
        ]));

        set("item_desc", ([
            "tieban" :      
            "鐵板歪歪斜斜地寫着：方人智到此一遊，空手悻悻而歸。\n",
        ]) );
        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6311);
        set("coor/z", -10);
        setup();
}

void init()
{
        add_action("do_press", "press");
}

int do_press(string arg)
{
        string p;

        p=sprintf("%d",query("passwd", this_player()));
        if( !p ) return notify_fail("林家先祖留下的銅錢的祕密你都沒有去研究過，就別瞎按了！\n");
        if( !arg || arg == "" )
        {
                write("別瞎按！\n");
                return 1;
        }
        if( arg == p )
        {
                message_vision("只聽得一陣隆隆的響聲由遠及近。\n", this_player());
                message_vision("石板緩緩移了開來，露出一個洞。\n", this_player());
                set("exits/enter", __DIR__"mishi");
                write("\n\n一個聲音提醒你：記住你的密碼，以後你就靠它來進出這裏了！\n\n");

                remove_call_out("close");
                call_out("close", 5, this_object());

                return 1;
        }
        else
        {
                write("你心想：老天保佑這次能蒙着！\n");
                if (random(10) != 8)
                {
                        message_vision("$N一陣亂按，什麼反應也沒有。\n", this_player());
                        return 1;
                }
                else
                {
                        message_vision("$N一陣亂按，突然石板的縫隙間射出一支毒箭！。\n", this_player());
                        this_player()->die();
                        return 1;
                }
        }
}

void close(object room)
{
        message("vision","轟隆隆的響聲響過之後，石板又合上了。\n", room);
        delete("exits/enter", room);
}