// Room: /d/huanggong/cininggong.c

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "慈寧宮");
        set("long", @LONG
這是太后的寢宮。. 這裏也是太后垂簾聽政之處。曾經主宰天下數
十年的朝廷政令，就出自你所在的女主人之手。東西兩面是暖閣。東暖
閣裏是太后的雕花大牀 (bed)。北面是個大佛堂，有清一代，太后除了
祭祀薩滿，幾乎無一例外地禮佛。
LONG
        );
        set("opened", 1);
        set("item_desc", ([
                "bed" : "太后老婊子的牀，看什麼看！\n",
        ]));
        set("exits", ([
                "south" : __DIR__"ciningmen",
                "north" : __DIR__"dafotang",
        ]));
        set("objects", ([
                __DIR__"npc/leichu" : 1,
                __DIR__"npc/dengbingchun" : 1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7741);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_open", "open");
        add_action("do_open", "dakai");
        add_action("do_open", "xiangkai");
}

int do_open(string arg)
{
        object me, obj;

        me = this_player();
        if( !arg || arg!="bed" )
              return notify_fail("你要打開什麼？\n");
        message_vision(YEL
"$N掀開被褥，見牀板上有個小銅環，伸指一拉，一塊闊約一尺，長約
二尺的木板應手而起，下面是個長方形的暗格，赫然......\n" NOR,me);
        if ( query("opened") != 1)
        {
                message_vision(HIR"什麼都沒有！\n" NOR,me);
                return 1 ;
        }
        message_vision(HIY"放着三部經書！\n" NOR,me);
        obj = new("/d/beijing/obj/book14_3");
        obj -> move(this_object());
        obj = new("/d/beijing/obj/book14_4");
        obj -> move(this_object());
        obj = new("/d/beijing/obj/book14_6");
        obj -> move(this_object());
        addn("opened", -1);
        return 1;
}