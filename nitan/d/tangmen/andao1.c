//andao1.c                四川唐門─地道

inherit ROOM;

void create()
{
        set("short","地道");
        set("long",
"這是一條地道。一進入這裡四周突然變的漆黑一團，你什麼都看不見\n"
"，走在裡面你總覺得有無數雙眼睛在盯著你看，但是四周又毫無聲息，好\n"
"象掉下一根針都可能聽到。北邊隱隱又一絲光亮傳來。\n"
);
        set("exits",([
                "south" : __DIR__"andao2",
                "north" : __DIR__"didao4",
        ]));
        setup();
        replace_program(ROOM);
}