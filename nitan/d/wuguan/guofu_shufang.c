inherit ROOM;

void create()
{
	set("short", "書房");
	set("long", @LONG
這是郭靖的書房。右邊是書架，上面陳列着道家和儒家的
一些典籍，卻沒有一本與武學有關的書。左邊靠窗的地方擺着
一張木桌，上面放着筆墨紙硯，邊上放着幾本書，擺放得整整
齊齊，搽拭得一塵不染，閣裏到處被打掃得一塵不染，窗明幾
淨，可以看到外面松竹掩映，時有微風入户，門後桌上還燃着
一爐檀香，氲氲的香氣輕輕橫散，使人俗念盡消，心情完全平
靜下來。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
		"south" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}
