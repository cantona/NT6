//menwei.c                四川唐門—差房

inherit ROOM;

void create()
{
        set("short", "差房");
        set("long",
"這裏是蓮藕小築的差房。平常唐門的下人們都喜歡聚在這裏比較各自\n"
"主人的武功高低，不過可不要小瞧這些下人，其中也不乏高手。這裏往東\n"
"是亭榭水閣。\n"
);
        set("exits", ([        "east" : __DIR__"shuige1",]));
        set("objects", ([__DIR__"npc/menwei" : 2,]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}