#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "禪室");
        set("long", @LONG
這裡是僧人門參禪打坐的地方。側壁一列禪床讓人看了就想到該
想的事。正對門的牆上有個黃銅輪盤(lunpan)，上面刻著些希奇古怪
的花紋，不知是什麼意思。
LONG );
        set("no_fight", 1);
        set("sleep_room", 1);
        set("no_steal", 1);

        set("exits", ([
                "east"  : __DIR__"tiantai",
                "south" : __DIR__"houdian",
        ]));

        set("item_desc", ([
                "lunpan": YEL "\n這是一個由黃銅所鑄的大輪盤，輪盤上面"
                          "刻著許多希奇古怪的花\n紋，全是和風水有關。"
                          "看樣子你可以轉(turn)動它。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_turn", "turn");
}

int do_turn(string arg)
{
        object me = this_player();

        if (! arg || arg != "lunpan")
                return notify_fail("你要轉動什麼？\n");

        message_vision(HIY "\n$N" HIY "使勁轉動輪盤，地面忽然「喀喀喀」現"
                       "出一個洞口。\n\n" NOR, me);
        set("exits/down", __DIR__"midao");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "地面忽然「喀喀喀」縮回原地，把密道的入口擋"
                          "住了。\n" NOR, room);
        delete("exits/down", room);
}