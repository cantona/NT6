//huayuan.c                四川唐門—花園

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long",
"從漆黑的地道中出來,你發現自己竟是置身於一個極精緻的小花園中,\n"
"紅梅綠竹,青松翠柏,佈置得頗具匠心,往南去是一間青石小屋。\n"
);
        set("exits", ([
                        "east" : __DIR__"andao2",
                        "south" : __DIR__"shiwu",
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}