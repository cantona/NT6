inherit ROOM;

void create()
{
	set("short", "郭府花園");
	set("long", @LONG
這裡是郭府的花園，園內假山林立，西邊種著些青竹，東
邊是幾棵枝葉茂盛的木筆花樹。你一走進來，就聞到一陣陣清
新的、淡淡的花香。
LONG);
        set("no_fight", 1);
	set("exits", ([
		"east"  : __DIR__"guofu_woshigh",
		"west"  : __DIR__"guofu_kefang",
		"south" : __DIR__"guofu_lang5",
		"north" : __DIR__"guofu_shufang",
	]));
	setup();
        (CLASS_D("taohua") + "/rong")->come_here();
}

void reset()
{
        ::reset();
        (CLASS_D("taohua") + "/rong")->come_here();
}

