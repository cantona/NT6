//Room: dgtsheshenya.c 睹光台舍身崖
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "睹光台舍身崖");
        set("long", @LONG
從臥雲庵出來，這裡是看日出、雲海、佛光、神燈之地。台下深
崖萬丈，陡徹無底，雲遮霧掩。極目四望，數百裡外的大小雪山皆歷
歷在目。因為這裡至高至潔，至險至奇，又至美至幻，常有人在這裡
投身雲海，舍此肉身塵世。　　金頂雲海，迷迷茫茫，籠罩四野，遠
接天際。雲海輕盪時，你在金頂，腳踏白雲，大有飄飄欲仙之感；當
雲濤迅猛湧來時，整個金頂都似在向前浮動，令人有乘舟欲風之意。
LONG );
        set("outdoors", "emei");
        set("exits",([ /* sizeof() == 1 */
                "north"     : __DIR__"duguangtai", 
/*
                "enter"    : __DIR__"woyunan",
                "east"     : __DIR__"duguangtai", 
*/
        ]));
        
        set("coor/x", -570);
        set("coor/y", -340);
        set("coor/z", 220);
        
        setup();
}

void init()
{
        object me;

        if (interactive(me = this_player()))
        {
                remove_call_out("clone_ji");
                call_out("clone_ji", 2,me);
        }
        add_action("do_sheshen","sheshen");
}

void clone_ji(object me)
{
        object *ob, obj;
        int i;

        if (! objectp(me) || environment(me) != this_object())
                return;

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if( query("id", ob[i]) == "jixiaofu" )
                return;
        }

        if( query("marks/ji", me) )
        {
                obj = new("/kungfu/class/emei/ji.c");
                obj->move(environment(me));
        }
}

int do_sheshen(object me)
{
        me = this_player();
        message_vision("$N覺得活著太沒意思了，決定舍身成仁。\n", me);
        message_vision("$N毅然跳出舍身崖，長聲尖叫，凄厲的聲音響徹山谷，隨著$N的的下落也急劇向下拉長。\n", me);
        if (me->query_skill("dodge", 1) >= 220)
        {
                me->move(__DIR__"st0");
                me->unconcious();
        } else
        {
                command("chat 有人跳下舍身崖自殺了。\n\n");
                me->move(__DIR__"st0");
                me->die();
        }
        return 1;
}
