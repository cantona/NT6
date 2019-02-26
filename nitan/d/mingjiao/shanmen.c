// Room: /d/mingjiao/shanmen.c
// Date: Java 97/04/3

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "明教山門");
        set("long", @LONG
一個巨大的天然石橋橫跨在兩片山壁之間，石橋正上方龍盤鳳舞
刻着兩個大字：『明教』。字跡有些剝落，看上去年代久遠。兩位三
十來歲的大漢手持鋼劍守在山門兩側。
LONG );
        set("exits", ([
                "westup" : __DIR__"shanlu1",
                "east" : __DIR__"tomen1",
        ]));
        set("outdoors", "mingjiao");
        set("objects",([
                __DIR__"npc/menwei1" : 2,
                __DIR__"npc/jieyinshi":1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i;

        if (me->query_family() != "明教" &&
            me->query_family() != "武當派"  &&
            dir == "westup")
        {
                inv = all_inventory(me);
                for(i=sizeof(inv)-1; i>=0; i--)
                        if(query("weapon_prop", inv[i]) && ((string)query("equipped", inv[i])=="wielded"))
                                if(objectp(present("da han", environment(me))))
                                        return notify_fail("大漢攔住你説道：這位" +
                                                RANK_D->query_respect(me) + "請放下兵刃。我教教規嚴"
                                                "厲，外客不\n得持兵刃上山。請見諒。\n");
        }
        return ::valid_leave(me, dir);
}
