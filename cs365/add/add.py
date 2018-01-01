def add(nums):
    if len(nums) == 1: 
        return nums[0]
    else:
        return add(nums[0:len(nums)/2]) + add(nums[len(nums)/2:])

print add([3,4,6,9,12])
