// Room: /d/changan/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "長安城商棧");
        set("long", @LONG
這裡就是著名的京城商棧，京城買賣商品的集散地，也是富商大
賈雲集之所，由京城商會控制。在京城大宗商品的買賣都要通過這裡
進行。門口掛著一塊木牌(sign)。
LONG );

        set("item_desc",([
        "sign" : "
list                    查看當地各種商品的價格。
shou <數量> 商品        收購一定數量的商品。
pao <數量> 商品         在本地拋售一定數量的商品。
fasong                  將你在本地的貨物發往其它的地點。
\n",
]));

        set("exits",([
        "south" : __DIR__"majiu",
]));


        // 初始貨物數量
        set("all_wares",([
        "rice" :   187500,     //1
        "wheat" :  187500,    //2
        "corn" :   187500,     //3
        "ganzhe" : 187500,   //4
        "goober" : 187500,   //5
        "silk" :    37500,     //6
        "cloth" :  187500,    //7
        "zxiu" :    37500,     //8
        "iron" :   187500,     //9
        "tong" :   187500,     //10
        "diamand" : 37500,  //11
        "suis" :   187500,     //12
        "gold" :    18750,      //13
        "silver" :  37500,   //14
        "picture" : 0,      //15  需要
        "jxiu" :    18750,      //16
        "book" :    18750,      //17
        "vase" :    18750,      //18
        "harm" :   187500,     //19
        "guiy" :    37500,     //20
        "meat" :   187500,     //21
        "fish" :   187500,     //22
        "orange" : 187500,   //23
        "tea" :    187500,      //24
        "yye" :    187500,      //25
        "shen" :    18750,      //26
        "deer" :    18750,      //27
        "sdan" :    18750,      //28
        "bamboo" : 300000,   //29
        "pei" :     18750,       //30
        "hairpin" : 18750,   //31
        "qilin" :  187500,    //32  本地
        "guan" :   187500,     //33  本地
        "ddai" :    18750,      //34
        "mxia" :    18750,      //35
        "jade" :    18750,      //36
        "pearl" :   18750,     //37
        "bonsai" :  18750,    //38
        "spear" :  187500,    //39
        "sword" :  187500,    //40
        "blade" :  187500,    //41
        "shield" : 300000,   //42
        "jian" :   300000,     //43
        "armor" :  187500,    //44
        "wood" :   187500,     //45
        "stone" :  300000,    //46
        "cansi" :       0,        //47  需要
        "cotton" : 300000,   //48
        "salt" :   300000,     //49 
        "paper" :   37500,    //50
]));

        // 各類商品的價格指數
        set("kind_rate",([
        "picture" : 122, //15  需要
        "qilin" : 77,    //32  本地
        "guan" : 78,     //33  本地
        "cansi" : 125,   //47  需要
]));
 
        set("coor/x", -10750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}