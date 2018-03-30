import sys
import random
import numpy as np
import matplotlib.pyplot as plt

def bandit(action, mu, sigma, k): #TODO change this
    env_reward = None
    left = None
    right = None
    if (k%2==0):
        left = np.random.normal(mu, sigma, k/2)
        right = np.random.normal(mu, sigma, k/2)
    else:
        left = np.random.normal(mu, sigma, (k-1)/2)
        right = np.random.normal(mu, sigma, (k+1)/2)
    left = np.sort(left)
    right = np.sort(right)[::-1]
    env_reward = np.concatenate([left, right])
    return env_reward[action]

if __name__ == "__main__":
    Q = [] # Estimate value
    N = [] # Actions
    reward_hist = []
    k = 0
    prob = 0
    mu = 0 # defaults mean
    sigma = 0.1 # default standard deviation

    k = int(sys.argv[1]) # number of arms
    prob = float(sys.argv[2]) # [0,1] chance of random action
    mu = float(sys.argv[3]) # mean
    sigma = float(sys.argv[4]) # standard deviation

    Q = [0] * k
    N = [0] * k
    
    f = open('D:\\Users\\AlanJ\\Documents\\GitHub\\IDLE-Task-RL\\karmBandit.txt', 'w+')

    for _ in range(0, 100):
        choosen_action = 0
        if (random.uniform(0, 1) <= (1-prob)):
            max_estimate = max(Q)
            max_actions = []
            i = 0
            for q in Q:
                if q == max_estimate:
                    max_actions.append(i)
                i+=1
            choosen_action = random.choice(max_actions)
        else:
            choosen_action = random.randint(0, k-1)
            print choosen_action
        reward = bandit(choosen_action, mu, sigma, k)
        N[choosen_action] += 1
        Q[choosen_action] = Q[choosen_action] + (reward-Q[choosen_action])/N[choosen_action]
        reward_hist.append(reward)

        f.write("A={}\tR={}\n".format(choosen_action, reward))
    f.close()

    plt.plot(N) # plotting by columns
    plt.show()