inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
一步跨進，腳下喀喇一聲，踏碎了一堆枯骨。這是一條僅
可容身的狹長甬道，刀劍四散，到處都是骸骨。火光下只見門
後刀痕累累，斑駁凹凸。走完甬道，慢慢前行，跨過一堆堆白
骨，轉了個彎，前面突然出現一座大殿。
LONG);
        set("exits", ([
                "east" : __DIR__"dadian",
                "south" : __DIR__"yongdao3",
        ]));

        set("objects", ([
                __DIR__"obj/yufu" : random(2),
                __DIR__"obj/yudao" : random(2),
                __DIR__"obj/yujian" : random(2),
                __DIR__"obj/skeleton" : random(3) + 1,
        ]));

        setup();
        replace_program(ROOM);
}