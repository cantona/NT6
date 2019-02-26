inherit ROOM;

void create()
{
        set("short", "高昌廢墟");
        set("long", @LONG
陡然間眼前一片空曠，此時朝陽初升，只見景色奇麗，莫
可名狀。一座白玉山峯參天而起，峯前一排排的都是房屋。千
百所房屋斷垣剩瓦，殘破不堪，已沒一座完整，但建築規模宏
大，氣象開朗，可見當年是一座十分繁榮的城市。
LONG);
        set("outdoors", "gaochang");

        set("exits", ([
                  "east" : __DIR__"shibi",
                  "west" : __DIR__"feixu2",
        ]));

        setup();
        replace_program(ROOM);
}