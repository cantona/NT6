// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;
string look_bei();
void create()
{
        set("short", "果子溝");
        set("long", @LONG
果子溝的野果樹，主要分佈在頭台附近的幾十道山嶺上，所以頭
台的花最多最豔。那五色的野果花，順着山坡一溜兒往上開，一樹樹，
一簇簇，紅豔豔，白閃閃，直上山頂，與天上的彩雲連接，千姿百態，
如錦緞，似朝霞。幾裏地外也能聞到馥郁的花香。溝底有塊小小石碑
(bei)。
LONG );
        set("exits", ([
                "east" : "/d/xingxiu/ertai",
                "northup" : "/d/xingxiu/tianchi",
        ]));
        set("objects", ([
                "/d/wudang/obj/mitao" : 1,
                "/d/xingxiu/obj/hamigua" : 1,
        ]));
        set("item_desc",([
                "bei"         :       (: look_bei :),
        ]));
        set("cost", 2);
        set("outdoors", "tianshan");

        setup();
}
string look_bei()
{
        return
        "\n"
        "                   不    樹    地\n\n"
        "                   露    陰    皆\n\n"
        "             耶    日    蓊    林\n"
        "             律                  \n"
        "             楚    色    鬱    檎\n"
        "             才                  \n";
}