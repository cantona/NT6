// jinliange.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "金蓮閣");
        set("long", @LONG
這金蓮閣位於終南山山腰間，形勢頗為險要。金蓮閣後有一口碗
口粗的湧泉，泉水碧綠透明，香甜誘人，在當地頗為有名，不少人特
別來此，只為了取這ㄦ的水來泡茶。那寺前的一塊石碑(shibei)，刻
了一收首王維的詩。往南看去是一條山路。往西走是一條蜿蜒的山路。
LONG
        );
        set("resource/water", 1);
        set("item_desc", ([
                "shibei"  : 
"

                欲 分 白 太
                投 野 雲 乙
                何 中 回 近  終
                處 峰 望 天  南
                宿 變 合 都  山
                ， ， ， ，
                隔 陰 青 連
                水 晴 靄 山  王
                問 眾 入 到  維
                樵 壑 看 海
                夫 殊 無 隅
                。 ； 。 ；

",
        ]));

        set("outdoors", "zhongnan");
        set("exits", ([
                "westup"     : __DIR__"shanlu10",
                "southdown"  : __DIR__"shanlu9",
        ]));
        set("objects", ([
                __DIR__"npc/yu" : 1,
        ]));

        set("coor/x", -3130);
        set("coor/y", 30);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
