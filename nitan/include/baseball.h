
#define BASEINCOME              400000000
#define TICKTIME                14
#define POSTSEASON_TICKTIME     9
#define PREPARETIME             600
#define HINTTIMES               6

#define HANDSIDE_NONE           0
#define HANDSIDE_LEFTHAND       (1<<0)
#define HANDSIDE_RIGHTHAND      (1<<1)
#define HANDSIDE_TWOHANDS       (HANDSIDE_LEFTHAND|HANDSIDE_RIGHTHAND)

#define RECORD_TEAM                     0
#define RECORD_PLAYER           1
#define RECORD_SPECIAL          2

#define STATUS_IDLE                     0
#define STATUS_PREPARING        1
#define STATUS_PLAYING          2

#define TICK                    0       // 計數
#define TEAM1                   1       // 主場球隊
#define TEAM2                   2       // 客場球隊
#define INNING                  3       // 局數
#define OUT                             4       // 出局數
#define STRIKE                  5       // 好球
#define BALL                    6       // 壞球
#define RUNNER1ST               7       // 一壘跑者
#define RUNNER2ND               8       // 二壘跑者
#define RUNNER3RD               9       // 三壘跑者
#define TEAM1NUMBER             10      // 主場球隊目前棒次
#define TEAM2NUMBER             11      // 客場球隊目前棒次
#define TEAM1SCORE              12      // 主場球隊得分
#define TEAM2SCORE              13      // 客場球隊得分
#define TEAM1HIT                14      // 主場球隊安打數
#define TEAM2HIT                15      // 客場球隊安打數
#define TEAM1MISS               16      // 主場球隊失誤數
#define TEAM2MISS               17      // 客場球隊失誤數
#define TEAM1K                  18      // 主場球隊投手三振數
#define TEAM2K                  19      // 客場球隊投手三振數
#define TEAM1WALK               20      // 主場球隊保送數
#define TEAM2WALK               21      // 客場球隊保送數

#define BASETYPE_STRIKEOUT              0       // 三振
#define BASETYPE_BALL                   1       // 保送上壘
#define BASETYPE_HIT                    2       // 安打上壘
#define BASETYPE_BUNT                   3       // 觸擊短打
#define BASETYPE_TOUCHKILL              4       // 刺殺
#define BASETYPE_CATCHKILL              5       // 接殺
#define BASETYPE_DOUBLEPLAY             6       // 雙殺
#define BASETYPE_TRIPLEPLAY             7       // 三殺
#define BASETYPE_STEAL                  8       // 盜壘

#define SCORETYPE_HOMERUN               1       // 全壘打
#define SCORETYPE_FOURBALL              2       // 保送
#define SCORETYPE_SACRIFICE             3       // 犧牲打
#define SCORETYPE_HIT                   4       // 安打

#define HINTTYPE_BATTER                 1       
#define HINTTYPE_PITCHER                2       
#define HINTTYPE_BUNT                   3       
#define HINTTYPE_WALK                   4

