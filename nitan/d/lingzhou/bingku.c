// Room: /d/lingzhou/bingku.c

inherit ROOM;

void create()
{
        set("short", "冰窟");
        set("long", @LONG
這裡是皇宮裡儲藏食物的所在，上下三層，到處整齊的碼著巨大的
冰塊。平時決無人來，只有夏天的時候御膳房的人偶來光顧。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"yushanfang",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}