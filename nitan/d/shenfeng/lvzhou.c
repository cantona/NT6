inherit ROOM;

void create()
{
        set("short", "沙漠綠洲");
        set("long", @LONG
你腳下的流沙已經不見，一個小小的湖泊呈現在你的眼前。
湖裏的水雖然只有二指厚，卻很清澈。在酷熱的風中，湖水仍
是那麼的清涼。一彎清流由北往南注入湖中。向西凝望，一座
雪白的山峯皎潔如玉。仰望峯巔，崇敬之心，油然而生。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "east" : __DIR__"shamo3",
                  "west" : __DIR__"xiaojing",
                  "north" : __DIR__"lake1",
        ]));
        setup();
        replace_program(ROOM);
}