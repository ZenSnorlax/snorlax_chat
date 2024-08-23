function calculateSum() {
    // 获取输入框的值
    const leftValue = document.getElementById('left_value').value;
    const rightValue = document.getElementById('right_value').value;

    // 将输入的值转换为数字
    const num1 = parseFloat(leftValue);
    const num2 = parseFloat(rightValue);

    // 检查输入是否为数字
    if (isNaN(num1) || isNaN(num2)) {
        alert('请输入有效的数字');
        return;
    }

    // 计算两个数字的和
    const sum = num1 + num2;

    // 将结果显示在页面上
    document.getElementById('result').value = sum; // 修改结果框的值
}

// 获取按钮元素
let btn = document.querySelector(".btn");

// 为按钮添加点击事件监听器
btn.addEventListener("click", calculateSum);
