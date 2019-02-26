#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武大廳"NOR);
        set("long", @LONG
這是一個寬敞的大房間，靠北牆搭着一個巨大的擂台(leitai)，
擂台後被一塊布簾遮擋的密密實實，但是一股濃厚的殺氣仍然從布簾
後散發出來，瀰漫在空氣裏，直鑽入你內心。在東面牆上，懸掛着偌
大的一個大匾(dabian)。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("item_desc",([
            "leitai" : "一個四四方方的大擂台，你可以跳(jump)上去。\n",
    ]));

    set("exits", ([
        "south"  : "/d/city/biwu_road",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}

void init()
{
    add_action("do_no","get");
    add_action("do_no","put");
    add_action("do_no","drop");
    add_action("do_no","summon");
    add_action("do_no","eat");
    add_action("do_no","drink");
    add_action("do_no","guard");
    add_action("do_jump","jump");
    add_action("do_look","look");
}

int do_no()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在這裏你想幹什麼？\n");
    return 1;
}

int do_look(string arg)
{
    string msg;
    int i;
    mapping paiming;

    if (arg != "dabian") return 0;
    paiming = COMPETE_D->query_tops();
    msg = HIC "      *          雄       霸       天       下          *\n"NOR;
    msg += HIC "-------------------------------------------------------------\n";
    msg += "\n";
    for (i = 0;i < sizeof(paiming);i++)
{
            msg += HIY + "   【天下第" + chinese_number(i+1) + "】 " + NOR + paiming[i]["title"] + "\n";
            msg += "\n";
}
    msg += HIC "-------------------------------------------------------------\n";
    write(msg);
    return 1;
}

int do_jump(string arg)
{
    object me;

    me = this_player();

    if (arg != "leitai")
    {
            tell_object(me,"你要往哪裏跳啊？\n");
            return 1;
    }

    if (wizardp(me))
    {
            tell_object(me,"你是巫師啊，就別來跟玩家爭什麼第一第二了！\n");
            return 1;
    }

    if (COMPETE_D->join_competition(me)) 
            return 1;
}