#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "茶室");
        set("long", @LONG
滿屋的果香和茶香，沁人心脾。山西面的茶農們因感激武當弟子
保護他們免受土匪的騷亂和官府的苛捐雜稅，每年開春採茶季節，總
要送來上好的茶葉。這茶葉由少女在三更至日出間採摘，放在懷中用
體溫焙制，得天地精華，匯處子體香，故名女兒香，據說喝了能提精
補神，十分珍貴。
LONG );
        set("exits", ([
                "north" : __DIR__"donglang2",
        ]));
        set("objects",([
                __DIR__"npc/xiaocui" : 1,
                __DIR__"obj/mitao" : 3,
                __DIR__"obj/dawancha" : 4,
        ]));
        set("coor/x", -350);
        set("coor/y", -310);
        set("coor/z", 90);
        setup();
}