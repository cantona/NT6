inherit ROOM;

void create()
{
        set("short", "大湖");
        set("long", @LONG
轉了幾個彎，從一排參天青鬆中穿了出去，登時驚得呆了。
眼前一片大湖，湖的南端又是一條大瀑布，水花四濺，日光映
照，現出一條彩虹，湖周花樹參差，雜花紅白相間，倒映在碧
綠的湖水之中，奇麗莫名。遠處是大片青草平原，無邊無際的
延伸出去，與天相接。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "south" : __DIR__"caoyuan1",
                "east" : __DIR__"lake3",
                "west" : __DIR__"huijiang5",
        ]));

        setup();
        replace_program(ROOM);
}