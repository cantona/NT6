inherit ROOM;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這是一間佈置精美的房間，正中是一長紅木八仙桌，左手一
個大書架幾乎佔了一面牆，仔細看上面全是醫學經脈類的典籍，
居然沒有一本武功書籍。
LONG
        );
        set("exits", ([
  "south" : __DIR__"yitong",
]));

        setup();
        replace_program(ROOM);
}
