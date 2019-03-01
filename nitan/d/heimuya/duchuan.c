// Room: /d/shaolin/duchuan.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "渡船");
        set("long", @LONG
黃河上的小舟都是這種很簡陋的小舟。一位中年艄公正站在船尾
吃力地掌舵，一位膀子壯碩的小夥子也在船頭用勁地划水撐船。黃河
水流湍急，船下滑很快，橫渡卻很慢。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "heimuya");
        setup();
        replace_program(ROOM);
}
