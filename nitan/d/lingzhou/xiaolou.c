// Room: /d/lingzhou/xiaolou.c

inherit ROOM;

void create()
{
        set("short", "小樓");
        set("long", @LONG
這是一幢三層樓的木製建築。端的是金碧輝煌，氣象萬千。赫連鐵
樹住在這裏。底層是一排落地長窗和硃紅色的圓柱。二樓有個小陽台，
三樓樓頂的琉璃瓦在陽光下閃閃發光，和皇城大殿的金頂同為全城都可
看到的建築。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "out" : __DIR__"jjdayuan",
        ]));
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/yahuan" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2905);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}