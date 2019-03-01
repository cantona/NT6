//andao2.c                四川唐門─地道

inherit ROOM;

void create()
{
        set("short","地道");
        set("long",
"這裡,四周漆黑一團,你好象什麼都看不見似的走在裡面,你不覺想到\n"
"這似乎在每個角落都藏著無限殺機,太恐怖了四周毫無聲息，好象掉下一\n"
"根針都可能聽到。\n"
);
        set("exits",([
                "north" : __DIR__"andao1",
                "west" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}