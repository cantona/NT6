// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "大殿");
        set("long", @LONG
而更使人感到這個空間像曠野的，是在河流兩旁，雖然實際上沒
有青草，可是叫人一看就知道，那是一片草原，是一片水草豐美，最
適合放牧的地方，因為在整個空間之中，至少有超過兩百匹的『馬』
那些馬，完全和實在的馬一樣大小，它們神態生動，有的在俯首飲水，
有的在地上打滾，有的在追逐，有的在踢蹄，每一匹馬，都有它不同
的神態，一個眼花之下，會以為那些馬全是活的。
LONG );
    set("exits", ([
        "south" :__DIR__"dadian",
        "north" :__DIR__"dadian3",
]));
        set("item_desc", ([
  "馬" : "那些馬，全是陶制的，每一匹馬的位置，顯然也曾經過一藝術的精心
安排，疏密有致，一點也不覺得擁擠，反倒襯得整個空間更加空曠。
",
]));
    setup();
    replace_program(ROOM);
}