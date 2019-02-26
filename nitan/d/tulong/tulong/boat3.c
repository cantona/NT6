inherit ROOM;
void create()
{
        set("short","船上");
        set("long", @LONG
一隻大江船，比尋常的船大了許多，此時大船已經靠岸，隨時可以從甲板(d
eck)上跳下去。
LONG );
        set("item_desc", ([
                "deck" : "大船的甲板，已經被海水侵蝕得腐爛不堪。\n",
        ]));

        set("no_fight",1);

setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
        return notify_fail("你要往哪裏跳？\n");

        if( arg=="deck" ) 
        {
                if (me->is_busy() )
                {
                        return notify_fail("你的動作還沒有完成，不能移動。\n");
                        return 1; 
                }

                message("vision",
                        me->name() + "輕輕一躍，從大船的甲板上跳了下來。\n",
                        environment(me), ({me}) );
                me->move("/d/tulong/tulong/shatan");
                message("vision",
                        me->name() + "跳下了船，從遠處的海邊走了過來。\n",
                        environment(me), ({me}) );
                return 1;
        }
}       
