// Room: /d/xiakedao/xkroad5.c
// Modified by Java on Feb.14.1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "漁港");
        set("long", @LONG
這裡是個小小漁港。南面海面漂浮著幾艘小船，抬眼望，海天相
連，無邊無際。海鷗掠過浪尖，悠悠翩然。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "east"    : __DIR__"xkroad4",
        ]));
        set("objects", ([
                __DIR__"npc/shizhe" : 1,
                //__DIR__"npc/renter" : 1,
        ]));
        set("resource/quarry", ([
                "/clone/quarry/gui" :  40,
                "/clone/quarry/eyu" :  3,
                "/clone/quarry/haibei" :  5,
        ]));
        set("coor/x", -1410);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object ob, lingpai;
        string dir;

        if (arg != "boat")
                return notify_fail("你要去哪兒？\n" );

        ob = this_player();

        if (! lingpai = present("shangfa ling", ob))
                return notify_fail(HIC "船夫說道：“你沒有賞善罰惡令，不能到俠客島去！\n" NOR);

        message_vision(HIG "船夫點了點頭道：“既然閣下有賞善罰惡令，我就送你到俠客島去！”\n" NOR, ob);
        
        destruct(lingpai);

        message_vision("船夫一見有人上船，忙叫了一聲：開船嘍！\n", ob);
        message_vision("船夫升起帆，船就向南方航行。\n", ob);
        
        ob->move("/d/xiakedao/duchuan");
        tell_object(ob, BLU "你在海上航行了一整天.......\n" NOR ) ;
        call_out("home", 7, ob);
        return 1;
}

void home(object ob)
{
        if (! objectp(ob))
                return;

        tell_object(ob, "大船終于抵達了南海岸邊。你走下船來。\n");
        ob->move (__DIR__"haitan");
        message("vision", ob->name() + "下了小舟，走了過來。\n",
                environment(ob), ob);
}
