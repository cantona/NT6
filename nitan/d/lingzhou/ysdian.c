// Room: /d/lingzhou/ysdian.c

inherit ROOM;

void create()
{
        set("short", "議事殿");
        set("long", @LONG
這是皇宮裡最大的殿堂，也是西夏皇帝李元昊和群臣議事的地方。
地上舖著雪白的玉石板，兩邊是雪白的帷幄，靠北居中放著龍椅，上方
懸有一塊金匾，上書『天下為公』。是時西夏皇帝虛心納諫，廣招天下
賢士，西夏的國力達到了頂峰，南面的大宋和東面的大遼都頗為顧忌。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"gongsquare",
                "north" : __DIR__"huilang",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -6265);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}