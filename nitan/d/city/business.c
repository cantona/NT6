// Room: /d/fengtian/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "揚州商棧");
        set("long", @LONG
這裡就是著名的揚州商棧，揚州買賣商品的集散地，也是富商大
賈雲集之所，由揚州商會控制。在揚州大宗商品的買賣都要通過這裡
進行。門口掛著一塊木牌(sign)。
LONG );
        set("no_fight", 1); 
        set("item_desc",([
        "sign" : "
list                    查看當地各種商品的價格。
shou <數量> 商品        收購一定數量的商品。
pao <數量> 商品         在本地拋售一定數量的商品。
fasong                  將你在本地的貨物發往其它的地點。
\n",
]));

        // 初始貨物數量
        set("all_wares",([
        "rice" :    185000,     //1
        "wheat" :   185000,    //2
        "corn" :    185000,     //3
        "ganzhe" :  185000,   //4
        "goober" :  333000,   //5   本地
        "silk" :       370,       //6   需要
        "cloth" :   185000,    //7
        "zxiu" :     37000,     //8
        "iron" :    333000,     //9   本地
        "tong" :    185000,     //10
        "diamand" :  37000,  //11
        "suis" :    185000,     //12
        "gold" :     18500,      //13
        "silver" :   37000,   //14
        "picture" :  18500,   //15  
        "jxiu" :     18500,      //16
        "book" :     18500,      //17
        "vase" :     18500,      //18
        "harm" :         0,         //19  需要
        "guiy" :     37000,     //20
        "meat" :    185000,     //21
        "fish" :    185000,     //22
        "orange" :  185000,   //23
        "tea" :     185000,      //24
        "yye" :     185000,      //25
        "shen" :     18500,      //26
        "deer" :     18500,      //27
        "sdan" :     18500,      //28
        "bamboo" :  296000,   //29
        "pei" :      18500,       //30
        "hairpin" :  18500,   //31
        "qilin" :    18500,     //32  
        "guan" :     18500,      //33  
        "ddai" :     18500,      //34
        "mxia" :     18500,      //35
        "jade" :     18500,      //36
        "pearl" :    18500,     //37
        "bonsai" :   18500,    //38
        "spear" :   185000,    //39
        "sword" :   185000,    //40
        "blade" :   185000,    //41
        "shield" :  296000,   //42
        "jian" :    296000,     //43
        "armor" :   185000,    //44
        "wood" :    185000,     //45
        "stone" :   296000,    //46
        "cansi" :    37000,    //47  
        "cotton" :  296000,   //48
        "salt" :    296000,     //49 
        "paper" :    37000,    //50
]));

        // 各類商品的價格指數
        set("kind_rate",([
        "goober" : 73,      // 5  本地
        "silk" : 104,       // 6  需要
        "iron" : 98,        // 9  本地
        "harm" : 126,       //19  需要
]));

        set("exits",([
        "south" : __DIR__"majiu",
]));

	set("coor/x", 20);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}