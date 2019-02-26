// room: /d/xingxiu/nanjiang.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
這是一個雜貨鋪。房屋內鋪着地毯。店老闆坐在地毯上，旁邊堆着
他的貨。牆上有個牌子，是個價目表(sign)。
LONG
        );
        set("exits", ([ 
            "east" : __DIR__"yili",
        ]));
        set("objects", ([
                __DIR__"npc/maimaiti": 1
        ]) );
        set("item_desc", ([ /* sizeof() == 1 */
"sign" : "牌子上寫道：

中原錢幣通用。

       馬奶酒壺(hu)           一百文
       饢(nang)                      五十文
       火折(fire)             一百文
       哈密瓜(gua)            四十文
       冬不拉(dongbula)       一百文
       彎刀(wandao)       一千五百文
       羊皮(yangpi)           三百文
       伊犁馬(horse)          一千文 ( 售完 )
\n"
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -39100);
        set("coor/y", 13000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

 