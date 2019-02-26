#include <room.h>
#include <ansi.h>
#include <getconfig.h>
inherit ROOM;

int do_look(string arg);

void create()
{
        set("short", "英雄會館");
        set("long", @LONG
英雄會館也是鳳老爺的家業。常來這裏的人，都是有能耐有來頭
的。英雄會館裏圍着黑壓壓的一羣人，南方有一扇緊緊關閉的小門。
只有在每月一次的店鋪拍賣時「南霸天」鳳天南才會將它打開，在那
裏會見各處的商賈。小門旁掛着的一塊紅木牌子(paizi)上標寫着各家
店鋪拍賣的底價。
LONG );

        set("no_beg", 1);
        set("no_steal", 1);

        set("exits", ([
               "north" : __DIR__"street2",
        ]));

        set("objects", ([
                __DIR__"npc/fengyiming" : 1,
        ]));

        set("no_clean_up", 0);
	set("coor/x", -6580);
	set("coor/y", -9760);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_look", "look");

        if (wiz_level(this_player()) >= 3)
        {
                add_action("do_open", "open");
                add_action("do_close", "close");
        }
}

int valid_leave(object me, string dir)
{
        if (query("exits/south"))
        {
                if( (query("balance", me)<5000000
                 || query("weiwang", me)<0 )
                &&  dir == "south" && ! wizardp(me))
                        return notify_fail(CYN "鳳一鳴攔住你，冷笑道：以閣下的財"
                                           "產和地位，尚不足以進去。\n" NOR);
        }
        return ::valid_leave(me);
}

int do_open()
{
        object me = this_player();

        if (query("exits/south"))
                return notify_fail("門已經是開着的了。\n");

        set("exits/south", __DIR__"pmc");

        message_vision(HIY "$N" HIY "輕輕一推，將通向英雄會館的"
                       "小門開啟了。\n" NOR, me);

        shout(HIY "【商界傳聞】" NOR + WHT + me->name() + WHT "[" +
              query("id", me)+WHT"]開啟了佛山英雄會館的店鋪拍"
              "賣會的大門。\n" NOR);

        write("你開通了店鋪拍賣會的路徑。\n");
        return 1;
}

int do_close()
{
        object me = this_player();

        if (! query("exits/south"))
                return notify_fail("門已經是關着的了。\n");

        delete("exits/south");
        message_vision(WHT "$N" WHT "順手一帶，將通向拍賣後廳的"
                       "小門關上了。\n" NOR, me);
        return 1;
}

int do_look(string arg)
{
        int i, g;
        string msg;
        mapping *shop_record;

        if (arg != "paizi")
                return 0;

        if (! query("exits/south"))
        {
                write("現在尚未到拍賣店鋪的時間。\n");
                return 1;
        }

        shop_record = SHOP_D->query_shop();

        msg = LOCAL_MUD_NAME() + "店鋪拍賣底價表：\n"NOR;
        msg += HIY "┌─────────────────────────┐\n" NOR;

        msg += sprintf(HIY "│" NOR + WHT " %-18s%-18s%-13s" HIY "│\n" NOR,
                       "店鋪位置",
                       "店鋪名稱",
                       "拍賣底價");

        msg += HIY "├─────────────────────────┤\n" NOR;

        for (i = 0; i < sizeof(shop_record); i++)
        {
                g = shop_record[i]["price"];
                msg += sprintf(HIY "│" HIC " %s店鋪           "
                               HIG "%-16s" NOR +
                               YEL "黃金" + chinese_number(g) +
                               "兩    " HIY "│\n" NOR,
                               shop_record[i]["id"],
                               shop_record[i]["name"]);
        }
        msg += HIY "└─────────────────────────┘\n" NOR;
        msg += WHT "總共有" + chinese_number(sizeof(shop_record)) +
               WHT "家店鋪等待拍賣。\n";
        write(msg);
        return 1;
}