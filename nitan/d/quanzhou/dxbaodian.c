// Room: /d/quanzhou/dxbaodian.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "大雄寶殿");
        set("long", @LONG
石庭盡頭，便是大雄寶殿。相傳建殿之日，有紫雲飄繞蓋地，故又
稱「紫雲大殿」。殿上斗拱間雕着二十四尊美麗的「飛天」(fairies)， 
雁行整齊，展翅欲飛。殿內安祥跌坐五尊大佛，中間是唐玄宗的「御賜
佛像」釋加牟尼佛，餘者依次為南方寶生佛，西方阿彌陀佛，東方阿眾
佛，北方成就佛。後面是形態各異的十八羅漢。
LONG );
        set("item_desc", ([
                "fairies" : "
有的飛仙手持民間樂器，有的捧着文房四寶，清歌曼舞
屋樑之間，叫人彷彿聽見一派仙樂從天而降，隱約耳際。\n",
        ]));
        set("exits", ([
                "south" : __DIR__"tianwangdian",
                "north" : __DIR__"yuetai",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));
	set("coor/x", -920);
	set("coor/y", -7640);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}