// Room: /yangzhou/yueguan.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "月觀");
        set("long", @LONG
月觀坐西朝東，前臨湖濱，後瀕桂園，月光之下，粼粼水波，連成
一璧，實乃揚州賞月勝地。堂中懸掛著陳重慶題書“月觀”橫匾，堂前
掛一抱柱楹聯(lian)，為“揚州八怪”之一的鄭□橋所書。四壁懸掛四
片大型清代大理石掛屏，以海梅為框，櫻木為膛，每片各嵌有方圓二幅
天然山水紋飾大理石，並有題款，至為珍貴。面東護以木檻，檻外疏柳
三五株橫臥水際。
LONG );
        set("exits", ([
                "west"     : __DIR__"qishi",
                "northup"  : __DIR__"fengting",
        ]));
        set("item_desc", ([
                "lian" : HIC"
        月        雲
        來        起
        滿        一
        地        天
        水        山
\n"NOR,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 110);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}