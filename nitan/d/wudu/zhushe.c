inherit ROOM;

void create()
{
        set("short", "竹舍");
        set("long", @LONG
這是一間竹子搭成的房子，雖然簡陋但卻被主人收拾的乾乾淨淨。
一個羽扇綸巾，相貌清雅的文士正坐在案邊閒看三國，聽見腳步聲不
由抬起頭來。
LONG);

        set("exits", ([
                "north" : __DIR__"caoping",
        ]));
        set("objects", ([
                __DIR__"npc/zhuge": 1,
        ]));

        setup();
        replace_program(ROOM);
}