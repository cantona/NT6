// Room: /city/pomiao.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "土地廟");
        set("long", @LONG
這是一間破破爛爛的土地廟，廟裏破敗不堪，土地神像推在一旁，
樑上地下也佈滿了灰塵。一看就知道已經很久沒有人來清理過了。正中
放着個大香案，上面零亂地扔着幾根吃剩下來的雞骨頭。也許正是因為
隱蔽的原因吧，據説丐幫江南分舵就被設在此處。香案黑洞洞的，好像
下邊有個大洞(dong)。
LONG );
        set("region", "yz_zone");
        set("valid_startroom", 1);
//        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"shoushe",
                "east"  : __DIR__"sheyuan",
                "south" : "/d/city/ml4",
                "enter" : __DIR__"gbandao",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/lu" : 1,
                CLASS_D("gaibang") + "/peng" : 1,
        ]));
        create_door("enter", "小門", "out", DOOR_CLOSED);
        set("coor/x", 70);
        set("coor/y", 60);
        set("coor/z", 0);
        setup();
        "/clone/board/gaibang_r"->foo();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision",
                                me->name() + "運起丐幫縮骨功，一彎腰往香案下的洞裏鑽了進去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/undergb");
                        message("vision",
                                me->name() + "從洞裏走了進來。\n",
                                environment(me), ({me}) );
                        return 1;
                }
                else
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        object lu;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "丐幫") &&
            (dir == "west" || dir == "east") &&
                objectp(lu = present("lu youjiao", environment(me))) && living(lu))
           return notify_fail("魯有腳攔住你説：此處乃本幫禁地，請止步。\n");

        return ::valid_leave(me, dir);
}
