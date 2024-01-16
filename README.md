## :video_game:    **UE_RPG**    :video_game:
**-Team Members :** 박세은

**\- Title :** Monster Clash				

**\- 개발 툴 :** Unreal Engine5

**\- 스토리 :** 마법사로 전직하기 위해서 주어진 3개의 스테이지와 마지막 보스 스테이지에서 죽지않고 모든 몬스터를 처치하면 성공하는 게임        
**\- 맵 구성 :**				

      
 | <img width="1017" alt="스크린샷 2023-03-22 오후 5 32 34" src=""> |<img width="1017" alt="스크린샷 2023-03-22 오후 5 34 07" src="">|<img width="1017" alt="스크린샷 2023-03-22 오후 5 38 23" src="h">|<img width="1017" alt="스크린샷 2023-03-22 오후 5 37 20" src="">|
|:-----:|:-------:|:-------:|:-------:|
| Level1 | Level2 | Level3 | Level4 |


**\- 조작법 :**

좌우 및 시점 이동 : W A S D


그 외


B : 아이템 상호작용 / P : 포탈 이동 / 마우스 좌클릭 : 공격 / Shift : 캐릭터 능력치        
1,2,3 : 무기 변경        
M : 미니맵 / Q : 옵션 / I : 인벤토리 (Stage3) / S : 상점 (Stage3)


**<h2>주요 구현 기능**</h2>       

**1. 몬스터-플레이어 간의 생동감 있는 상호작용**	:        
몬스터와 플레이어가 서로 공격할 때, 블랙보드/비헤이버트리/애니메이션 몽타주/열거체를 활용하여 애니메이션이 알맞게 바뀌도록 구현



&nbsp;&nbsp;<img width="330" alt="그림1" src="">

• 몬스터1 블랙보드            
&nbsp;&nbsp;<img width="330" alt="그림1" src="">

• 몬스터1 행동트리        
&nbsp;&nbsp;<img width="330" alt="그림1" src="">

• 열거체        

*****
**2. 인벤토리, 상점 구현**





<img width="330" alt="그림2" src=""><img width="330" alt="그림3" src="">


 
참고 문서 : [[Ryan Laley] - How to Make an Inventory System in Unreal Engine 5](https://youtube.com/playlist?list=PL4G2bSPE_8umjCYXbq0v5IoV-Wi_WAxC3&feature=shared)


**3. 공격력 버프 구현**





<img width="330" alt="그림4" src=""><img width="330" alt="그림5" src="">



• Level 3 : 보물상자를 먹고 인벤토리 창에서 Use 하면 60초간 공격력이 버프 됨


**<h2>특징**</h2>

1. 기술 : 이전의 언리얼 프로젝트는 블루프린트만 사용했었지만, 이번 프로젝트에서는 C++ 언어도 활용하여 구현하였음        
   ㄴ[Term Project for 2022](https://github.com/se-ni/HY_Game-programming.git)
2. 배경 : 시간의 흐름을 표현하기 위해, Sky Sphere를 이용하여 하늘 색깔이 어두워지게 구현하였음



<h2>구현 시 아쉬웠던 점</h2>


\- 플레이어가 무기 변경하고 공격하면 몬스터와 상호작용 하지 못함 (기본적으로 장착된 무기랑만 상호작용 함)              
\- 인벤토리 구현 : 인벤토리에 대한 지식이나 정보가 매우 부족해서, 외국 유튜브를 보고 따라했기 때문에 정확한 개념 습득을 하지 못함        
\- UI의 디자인적인 퀄리티 : 개인 프로젝트다 보니 기능 구현에 집중을 해야했기 때문에 UI의 퀄리티가 아쉬움




<h2>참고 문서</h2>




[[Ryan Laley] - How to Make an Inventory System in Unreal Engine 5](https://youtube.com/playlist?list=PL4G2bSPE_8umjCYXbq0v5IoV-Wi_WAxC3&feature=shared)





[셀바이뮤직](https://www.googleadservices.com/pagead/aclk?sa=L&ai=DChcSEwjP8piw0eGDAxVsXQ8CHYCiCFAYABAAGgJ0Yg&ae=2&gclid=CjwKCAiA75itBhA6EiwAkho9e2C9tOg1FYten09pewbk7oIfknrQ6FsMfXtNyBwpEI77x4JInFgoEBoCwW4QAvD_BwE&ohost=www.google.com&cid=CAESVuD2ZSE6yuVmYNy1L91Kr6N2sUiDUija3DnioIHCsM6B7L2UaaKZEmmozsEgU-HzPa9r2kDJt6cRwh60QTiX6Qx7VPpriavA60uZTTnsdnc3khnowRDD&sig=AOD64_3cnNFmKzeYoAUlE-Ce0wkZJqZFMA&q&adurl&ved=2ahUKEwimpJSw0eGDAxWXcfUHHQyyAa0Q0Qx6BAgJEAE)


