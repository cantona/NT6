//room: tuyuan.c
inherit ROOM;

void create()
{
        set("short","兔苑");
        set("long", @LONG
這是個好玩的兔苑，幾只大白兔靜靜地蹲在綠草地上吃草。西南
方是竹園。西面傳來陣陣猛獸的嚎叫，東面有一個蛇園。
LONG );
        set("exits",([
                "east"      : __DIR__"sheyuan",
                "west"      : __DIR__"shoushe",
                "southwest" : __DIR__"zhuyuan",
        ]));
        set("outdoors", "baituo");
        set("objects",([
                __DIR__"npc/baitu" : 2,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20070);
        set("coor/z", 30);
        setup();
}