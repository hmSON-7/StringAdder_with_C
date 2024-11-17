#include <stdio.h>
#include <string.h>
#include <math.h>
#include "char_stack.h"

#define STR_MAX_SIZE 300
#define LIST_MAX_SIZE 150

int addPeeks(CharStack *stackList, int listIndex, int *carry, int *flag, int *checkResultNegative);

int main() {
    // 1단계 : 가산기 초기화 및 세팅
    CharStack stackList[STR_MAX_SIZE];
    char str[STR_MAX_SIZE];
    for (int i = 0; i < LIST_MAX_SIZE; i++) {
        initStack(&stackList[i]);
    }

    // 2단계 : 입력 안내 및 입력값 받기
    printf("===========================================\n");
    printf("더하고 싶은 숫자들을 입력해주세요. 숫자 사이에 다른 문자나 기호를 넣으면 서로 다른 숫자로 인식합니다.\n");
    printf("(입력은 최대 300자로 제한하며, 각 숫자는 150자리를 넘길 수 없습니다.)\n");
    scanf("%s", str);
    printf("===========================================\n\n");

    // 3단계 : 문자열 분리 및 숫자 추출
    int readerCnt = 0, listIndex = 0, negativeFlag = 0;
    while (readerCnt < strlen(str)) {
        if(str[readerCnt] == '-') {
            checkNegative(&stackList[listIndex], 1);
            negativeFlag = 1;
        } else if (str[readerCnt] >= '0' && str[readerCnt] <= '9') {
            push(&stackList[listIndex], str[readerCnt]);
        } else {
            if(negativeFlag) {
                negativeFlag = 0;
            }
            if(!isEmpty(&stackList[listIndex])) {
                listIndex++;
            }
        }
        readerCnt++;
    }

    if (!isEmpty(&stackList[listIndex])) {
        listIndex++;
    }

    for(int i=0; i<sizeof(stackList); i++) {
        if(stackList[i].negative) {
            printf("-");
        }

        for(int j=0; j<getSize(&stackList[i]); j++) {
            printf("%c", stackList[i].data[j]);
        }

        if(isEmpty(&stackList[i+1])) {
            break;
        }

        printf(" + ");
    }

    printf(" = ");

    // 4단계 : 각 자리수 별로 덧셈 계산
    // 각 스택에서 수를 하나씩 제거하여 더하기. 단, 빈 스택은 넘기기
    // 더한 값의 1의 자리 수는 연산 결과 스택에 푸시
    // 더한 값의 10의 자리수 이상은 캐리 변수에 저장하여 다음 연산에 포함
    // 남은 숫자가 없다면 연산 종료
    int carry = 0;
    int checkResultNegative = 0;
    CharStack result;
    initStack(&result);
    while(1) {
        int flag = 0;
        int sum = addPeeks(stackList, listIndex, &carry, &flag, &checkResultNegative);
        // 더 이상 더할 숫자가 없는 경우
        if(flag) {
            // 더 이상 더할 숫자는 없으나 캐리가 남는 경우를 고려
            if(sum != 0) push(&result, sum + '0');
            break;
        }

        push(&result, sum + '0');
    }

    // 5단계 : 연산 결과 출력
    if(checkResultNegative) {
        printf("-");
    }
    while(!isEmpty(&result)) {
        printf("%c", pop(&result));
    }

    return 0;
}

// 4-1 : 각 스택의 top을 하나씩 가져와 더하는 함수
int addPeeks(CharStack *stackList, int listIndex, int *carry, int *flag, int *checkResultNegative) {
    int sum = *carry;
    *carry = 0;
    *flag = 1;
    for(int i=0; i<listIndex; i++) {
        if(isEmpty(&stackList[i])) {
            continue;
        }

        *flag = 0;
        char n = pop(&stackList[i]) - '0';
        if(stackList[i].negative) {
            sum -= n;
        } else {
            sum += n;
        }
    }

    if (sum >= 0) {
        *carry = sum / 10;
        *checkResultNegative = 0;
    } else {
        *carry = abs(sum) / 10 * -1;
        *checkResultNegative = 1;
    }
    return abs(sum) % 10;
}