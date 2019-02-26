//andao2.c                四川唐門—地道

inherit ROOM;

void create()
{
        set("short","地道");
        set("long",
"這裏,四周漆黑一團,你好像什麼都看不見似的走在裏面,你不覺想到\n"
"這似乎在每個角落都藏着無限殺機,太恐怖了四周毫無聲息，好像掉下一\n"
"根針都可能聽到。\n"
);
        set("exits",([
                "north" : __DIR__"andao1",
                "west" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}