import sys
import random
import numpy as np
import matplotlib.pyplot as plt

def bandit(action, mu, sigma, k): #TODO change this
    env_reward = np.random.normal(mu, sigma, k)
    return env_reward[action]

if __name__ == "__main__":
    Q = [] # Estimate value
    N = [] # Actions
    reward_hist = []
    k = 0
    prob = 0
    mu = 0 # defaults mean
    sigma = 0.1 # default standard deviation

    k = int(sys.argv[1])
    prob = float(sys.argv[2]) # [0,1] chance of random action
    mu = float(sys.argv[3])
    sigma = float(sys.argv[4])

    print(k, prob, mu, sigma)

    Q = [0] * k
    N = [0] * k
    
    f = open('C:\\Users\\ahuang\\Documents\\GitHub\\IDLE-Task-RL\\karmBandit.txt', 'w+')

    for _ in range(0, 100000):
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
        reward = bandit(choosen_action, mu, sigma, k)
        N[choosen_action] += 1
        Q[choosen_action] = Q[choosen_action] + (reward-Q[choosen_action])/N[choosen_action]
        reward_hist.append(reward)

        f.write("A={}\tR={}\n".format(choosen_action, reward))
    f.close()

    plt.plot(N) # plotting by columns
    plt.show()