// Room: /d/yueyang/yueyanglou1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽樓");
        set("long", @LONG
岳陽樓始建於唐，背靠岳陽城，俯瞰洞庭湖，遙對君山島，北依長
江，南極湘江，登樓遠眺，一碧無垠，白帆點點，雲影波光，氣象萬千。
全樓高五丈，頂起飛檐，樓頂的形狀酷似一頂將軍頭盔，俗稱盔項。
    北宋巴陵郡守滕子京重修岳陽樓，憑欄遠眺，詩興大發：“湖水邊
天，天邊水，秋來分澄清。君是小蓬瀛，氣蒸雲夢澤，波撼岳陽城。帝
子有靈能鼓瑟，悽然依舊傷情。微聞蘭芷動芳馨，曲終人不見，江上數
峯青。”范仲淹應滕子京之請，為《岳陽樓記》共三百六十字，樓始“
先天下之憂而憂，後天下之樂而樂”而名傳。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "up"        : __DIR__"yueyanglou2",
                "south"     : __DIR__"xianmeiting",
                "north"     : __DIR__"sanzuiting",
                "eastdown"  : __DIR__"huaiputing",
                "northeast" : __DIR__"xiaoqiaomu",
        ]));
	set("coor/x", -6240);
	set("coor/y", -3000);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}